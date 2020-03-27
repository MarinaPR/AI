using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Laba1
{
    [Serializable]

    //------ часткова реалізація класа Person який реалізує клас IEquatable<Person>
    class Person : ICompatible<Person>, IEquatable<Person>
    {
        private string Name { get; }

        private bool isKnight() => Name.StartsWith(knightIdentifier);

        private static string knightIdentifier = "Рыцарь";


        public Person(string name)
        {
            Name = name;
        }

        public string Surname =>
            Regex.Matches(Name, @".(\d+)$")[0].Groups[1].Value;

        public bool isCompatible(List<Person> group)
        {
            var knight = group.Where(x => x.isKnight());
            var squire = group.Except(knight).ToList();
            if (knight.Count() == 0) return true;

            return squire.TrueForAll(sq =>
               knight.Where(x => x.isCompatible(sq)).Count() != 0);
        }

        public bool isCompatible(Person other) =>
            (isKnight() == other.isKnight()) || (Surname == other.Surname);

        public override string ToString()
        {
            return Name;
        }

        public bool Equals(Person other)
        {
            return Name == other.Name;
        }

    }
}
