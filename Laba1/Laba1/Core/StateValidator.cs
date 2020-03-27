using System.Collections.Generic;

namespace Laba1
{
    class StateValidator<T> : IValidator<T>
          where T : ICompatible<T>
    {
        public bool isValidGroup(List<T> group) =>
            group.TrueForAll(el => el.isCompatible(group));

        public bool isValidState(State<T> state) =>
            isValidGroup(state[Location.Left]) && isValidGroup(state[Location.Right]);
    }
}
