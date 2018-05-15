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
    [Route("api/Clients")]
    public class ClientsController : Controller
    {
        IClientsRepository clientRepository { get; set; }
        public ClientsController(IClientsRepository clientRepo)
        {
            clientRepository = clientRepo;
        }

        [HttpGet]
        public IEnumerable<Client> GetAll()
        {
            return clientRepository.FindAll();
        }

        [HttpGet("{id}")]
        public IActionResult Get(int id)
        {
            var client = clientRepository.Find(id);
            if (client != null)
                return new ObjectResult(client);
            else
                return NotFound();
        }

        [HttpPut("{id}")]
        public IActionResult Update(int id, [FromBody] Client clientData)
        {
            if (clientData == null || clientData.ID != id)
                return BadRequest();

            var client = clientRepository.Find(id);
            if (client == null)
                return NotFound();

            clientRepository.Update(id, clientData);
            return new NoContentResult();
        }
    }
}