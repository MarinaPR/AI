using System;
using System.Collections.Generic;

namespace Laba1
{
    class Program
    {
        static void Main(string[] args)
        {
            StateValidator<Person> validator = new StateValidator<Person>();
            Boat boat = new Boat(2, Location.Left);
            CrossSolver<Person> solver = new CrossSolver<Person>(validator, boat);

            var emptyList = new List<Person>();
            var finalList = new List<Person>(){
                    new Person("Рыцарь 1"),
                    new Person("Рыцарь 2"),
                    new Person("Рыцарь 3"),
                    new Person("Зброеносец 1"),
                    new Person("Зброеносец 2"),
                    new Person("Зброеносец 3"),
            };


            var initial = new State<Person>(Location.Left, finalList, emptyList, 0);
            var final = new State<Person>(Location.Right, emptyList, finalList, null);

            Action<List<State<Person>>> act =
                list =>
                {
                    Console.WriteLine("\n--------------Решение:----------------");
                    list.ForEach(state => Console.WriteLine(state + "\nГлубина: " + state.depth));
                    Console.ReadLine();
                    Environment.Exit(0);
                };


            int depth = 0;
            while (!solver.FindPath(initial, final, act, depth))
            {
                Console.WriteLine($"Не найдено с глубиной < {depth}");
                depth++;
            }

            Console.ReadLine();

        }
    }
}
