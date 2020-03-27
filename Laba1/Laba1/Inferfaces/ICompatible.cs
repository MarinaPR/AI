using System.Collections.Generic;

namespace Laba1
{
    interface ICompatible<T>
    {
        bool isCompatible(List<T> group);
    }
}

