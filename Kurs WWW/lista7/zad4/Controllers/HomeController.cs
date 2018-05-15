using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using FormValidation.Models;

namespace FormValidation.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Index(Car car)
        {
            DateTime res;

            if (!(DateTime.TryParse(car.dataRejestracji, out res)))
                ModelState.AddModelError("dataRejestracji", "Podana data jest niepoprawna");

            // Oglądamy zawartość ModelState pod debuggerem
            if (ModelState.IsValid)
            {
                return View("Success");
            }
            else
            {
            }
            return View();
        }
    }
}
