using System.Collections.Generic;

namespace Laba1
{
    interface IValidator<T>
    {
        bool isValidGroup(List<T> group);
        bool isValidState(State<T> state);
    }
}
