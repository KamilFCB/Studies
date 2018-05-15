using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using zad1.Models;

namespace zad1.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            var persons = new List<Person1>
            {
                new Person1{Id=1, FirstName="Andrzej", LastName="Kowalski"},
                new Person1{Id=2, FirstName="Jan", LastName="Nowak"}
            };
            return Json(persons);
            //return Content("Test");
            //return Redirect("http://www.ii.uni.wroc.pl/");
            //return new EmptyResult();
        }

        public IActionResult About()
        {
            ViewData["Message"] = "Your application description page.";

            return View();
        }

        public IActionResult Contact()
        {
            ViewData["Message"] = "Your contact page.";

            return View();
        }

        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
    internal class Person1
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
    }
}
