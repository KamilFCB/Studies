using Microsoft.AspNetCore.Mvc;
using RazorTemplates.Services;
using System;
using System.Net.Http;
using System.Threading.Tasks;

namespace RazorTemplates.ViewComponents
{
    public class GalleryViewComponent : ViewComponent
    {
        public GalleryViewComponent()
        {

        }


        public async Task<IViewComponentResult> InvokeAsync()
        {
            var client = new HttpClient();
            var img1 = await client.GetByteArrayAsync("https://images-na.ssl-images-amazon.com/images/I/41M9ItqBG%2BL.jpg");
            var img2 = await client.GetByteArrayAsync("https://www.wikipasy.pl/images/8/86/Real_Madryt_herb.png");
            var img3 = await client.GetByteArrayAsync("https://upload.wikimedia.org/wikipedia/commons/thumb/b/bd/Borussia_Dortmund_Banner.svg/1000px-Borussia_Dortmund_Banner.svg.png");
            var img4 = await client.GetByteArrayAsync("http://sklep.lovefootball.pl/img/p/1/4/7/3/1473-thickbox_default.jpg");


            var gm = new GalleryViewModel()
            {
                icon1 = Convert.ToBase64String(img1),
                icon2 = Convert.ToBase64String(img2),
                icon3 = Convert.ToBase64String(img3),
                icon4 = Convert.ToBase64String(img4)
            };

            return View(gm);
        }

        public class GalleryViewModel
        {
            public GalleryViewModel()
            {
            }

            public string icon1 { get; set; }
            public string icon2 { get; set; }
            public string icon3 { get; set; }
            public string icon4 { get; set; }
        }
    }
}