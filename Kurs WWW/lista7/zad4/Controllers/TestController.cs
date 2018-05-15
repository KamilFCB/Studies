using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Mime;
using StackExchange.Redis;
using System.IO;

namespace FormValidation.Controllers
{
    public class TestController : Controller
    {
        public IActionResult Index()
        {
            
            var persons = new List<Person1>
            {
                new Person1{Id=1, FirstName="Andrzej", LastName="Kowalski"},
                new Person1{Id=2, FirstName="Jan", LastName="Nowak"}
            };
            //return Json(persons);
            return Content("Test");
            //return Redirect("http://www.ii.uni.wroc.pl/");
            //return new EmptyResult();
        }
    }

    internal class Person1
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
    }
}