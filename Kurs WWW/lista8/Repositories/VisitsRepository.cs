using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using PoczekalniaApi.Models;

namespace PoczekalniaApi.Repositories
{
    public class VisitsRepository : IVisitsRepository
    {
        private List<Visit> Visits = new List<Visit>
        {
            new Visit {ID = 1, ClientID = 1, Data = "11-11-2011", Godzina = "11:15", Status = "zaplacone"},
            new Visit {ID = 2, ClientID = 1, Data = "21-11-2011", Godzina = "08:35", Status = "nie zaplacone"},
            new Visit {ID = 3, ClientID = 2, Data = "13-01-2011", Godzina = "9:15", Status = "nie zaplacone"}
        };

        public List<Visit> FindAll()
        {
            return Visits;
        }

        public List<Visit> Find(int clientId)
        {
            IEnumerable<Visit> tmp = Visits.FindAll(e => e.ClientID == clientId);
            return tmp.ToList();
            //IEnumerable<Visit> tmp = Visits.Where(e => e.ClientID == id);
        }

        public Visit FindVisit(int id)
        {
            return Visits.Find(e => e.ID == id);
        }

        public Visit Update(int id, Visit visit)
        {
            var v = Visits.Find(e => e.ID == id);
            if (v != null)
            {
                if (!string.IsNullOrEmpty(v.Data))
                    v.Data = visit.Data;
                if (!string.IsNullOrEmpty(v.Godzina))
                    v.Godzina = visit.Godzina;
            }

            return v;
        }

        public Visit Pay(int id)
        {
            var v = Visits.Find(e => e.ID == id);
            if (v != null)
            {
                if (!string.IsNullOrEmpty(v.Status))
                    v.Status = "zaplacone";
            }

            return v;
        }
    }
}
