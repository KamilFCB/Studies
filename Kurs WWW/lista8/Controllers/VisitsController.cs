using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using PoczekalniaApi.Models;
using PoczekalniaApi.Repositories;

namespace PoczekalniaApi.Controllers
{
    [Produces("application/json")]
    [Route("api/Visits")]
    public class VisitsController : Controller
    {
        IVisitsRepository visitRepository { get; set; }
        public VisitsController(IVisitsRepository visitRepo)
        {
            visitRepository = visitRepo;
        }

        [HttpGet]
        public IEnumerable<Visit> GetAll()
        {
            return visitRepository.FindAll();
        }

        [HttpGet("ClientVisits/{clientId}")]
        public IActionResult GetVisits(int clientId)
        {
            var visit = visitRepository.Find(clientId);
            if (visit != null)
                return new ObjectResult(visit);
            else
                return NotFound();
        }

        [HttpGet("Status/{id}")]
        public IActionResult GetStatus(int id)
        {
            var visit = visitRepository.FindVisit(id);
            if (visit != null)
                return new ObjectResult(visit);
            else
                return NotFound();
        }

        [HttpGet("Pay/{id}")]
        public IActionResult Pay(int id)
        {
            var visit = visitRepository.Pay(id);
            if (visit != null)
                return new ObjectResult(visit);
            else
                return NotFound();
        }

        [HttpPut("{id}")]
        public IActionResult Update(int id, [FromBody] Visit visitData)
        {
            if (visitData == null || visitData.ID != id)
                return BadRequest();

            var visit = visitRepository.Find(id);
            if (visit == null)
                return NotFound();

            visitRepository.Update(id, visitData);
            return new NoContentResult();
        }

    }
}
