using System;
using System.Collections.Generic;
using System.Linq;

namespace Laba1
{
    class CrossSolver<T>
    {
        private IValidator<T> _validator;
        private Boat boat;

        public CrossSolver(IValidator<T> checker, Boat bt)
        {
            _validator = checker;
            boat = bt;
        }

        private List<State<T>> GenerateStates(State<T> state)
        {
            List<State<T>> _possStates = new List<State<T>>();
            List<T> _source = state[state._boatPos];

            Location _destinationLocation = state._boatPos == Location.Left ? Location.Right : Location.Left;

            for (int i = 1; i <= boat.capacity; i++)
            {
                if (i > _source.Count) break;
                var groups = Combinations.GetCombinations(_source, i);

                foreach (var group in groups)
                {
                    State<T> copy = null;
                    if (_validator.isValidGroup(group))
                    {
                        copy = Serializer.DeepCopy(state);
                        group.ForEach(el =>
                        {
                            copy[state._boatPos].Remove(el);
                            copy[_destinationLocation].Add(el);
                        });

                        copy._boatPos = _destinationLocation;


                        if (_validator.isValidState(copy))
                        {
                            copy._step = $"Переправляем : " +
                           $"{string.Join(", ", group.ToList())}, " +
                           $"с {state._boatPos} на {_destinationLocation}";
                            _possStates.Add(copy);
                            copy.depth++;
                            _possStates.Add(copy);
                        }
                    }
                }
            }
            return _possStates.Distinct().ToList();
        }

        private static List<State<T>> UnWrapList(State<T> state)
        {
            List<State<T>> result = new List<State<T>>();
            State<T> current = Serializer.DeepCopy(state);
            while (current != null)
            {
                result.Add(current);
                current = current._parentState;
            }
            return result.Reverse<State<T>>().ToList();
        }

        public bool FindPath(State<T> initial, State<T> final, Action<List<State<T>>> action, int depth)
        {
            Stack<State<T>> states = new Stack<State<T>>();
            List<State<T>> history = new List<State<T>>();

            states.Push(initial);
            history.Add(initial);

            while (states.TryPop(out initial))
            {
                List<State<T>> gens = GenerateStates(initial).Where(x => !history.Contains(x) && (x.depth < depth)).ToList();
                history.AddRange(gens);

                gens.ForEach(gn =>
                {
                    gn._parentState = initial;
                    if (gn.Equals(final)) action(UnWrapList(gn));
                    states.Push(gn);
                });
            }
            return false;
        }
    }
}
