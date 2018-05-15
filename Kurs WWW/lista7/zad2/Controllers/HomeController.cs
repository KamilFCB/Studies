using Microsoft.AspNetCore.Mvc;
using MvcExample.Models;
using MvcExample.Services;
using PagedList;

namespace MvcExample.Controllers
{
    public class HomeController : Controller
    {
        private IPersonRepository _personRepository;

        public HomeController(IPersonRepository personRepository)
        {
            _personRepository = personRepository;
        }

        public IActionResult Index(int pageNumber = 1)
        {
            var model = _personRepository.GetAll();
            ViewData["Title"] = "Lista osób";
            ViewBag.Title = "Lista osób";
            //return Content("Hello");
            //return new ObjectResult(model);
            int pageSize = 3;
            return View(model.ToPagedList(pageNumber, pageSize));
        }

        public IActionResult Details(int id)
        {
            var model = _personRepository.GetById(id);
            ViewData["Title"] = model.FirstName + " " + model.LastName;
            return View(model);

        }
    }
}
