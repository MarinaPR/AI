using System;
using System.Collections.Generic;
using System.Text;

namespace Laba1
{
    [Serializable]
    class State<T> : IEquatable<State<T>>
    {
        //члени класу
        public Location _boatPos;
        private List<T> _left;
        private List<T> _right;
        public State<T> _parentState;
        public string _step;
        public int? depth;

        public List<T> this[Location loc]
        {
            get => loc == Location.Left ? _left : _right;
            set
            {
                var bank = loc == Location.Left ? _left : _right;
                bank = value;
            }
        }

        public State(Location boatPos, List<T> leftBank, List<T> rightBank, int? d)
        {
            _boatPos = boatPos;
            _left = leftBank;
            _right = rightBank;
            depth = d;
        }

        public bool Equals(State<T> other)
        {
            return EqualSequence(_left, other[Location.Left])
                && EqualSequence(_right, other[Location.Right])
                && (_boatPos == other._boatPos);
        }

        private bool EqualSequence(List<T> first, List<T> second) =>
            first.TrueForAll(x => second.Contains(x));

        public override string ToString()
        {
            return $"\n{(_step != null ? ("Шаг:\n" + _step) : string.Empty)} " +
                $"\nПозиция Лодки: {_boatPos}\n" +
                $"Левый Берег: {((_left.Count > 0) ? (string.Join(", ", _left)) : "   ")}\n" +
                $"Правый Берег: {((_right.Count > 0) ? (string.Join(", ", _right)) : "   ")}";
        }
    }
}
