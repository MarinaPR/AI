namespace Laba1
{
    enum Location  //перелік місця положення ( ліво право)
    {
        Left,
        Right
    }

    //--------параметризований конструктор Struct
    struct Boat  //-------створення обєкта структури Лодки
    {
        public int capacity;      //заповненість лодки
        public Location position;  //місце положення лодки

        public Boat(int cp, Location pos)
        {
            capacity = cp;
            position = pos;
        }
    }
}
