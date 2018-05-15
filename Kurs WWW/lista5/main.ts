$(document).ready( function() {
    let zaliczone:number = 0;
    let flaga:boolean = false;
    let start:boolean = false;
    let timer:number;
    
    $(".centrum").mouseleave(function(){
        czas_start();
    });
    
    $(".centrum").mouseenter(function()
    {
        czas_stop();
    });
    
    $(".cel1").mouseenter(function()
    {
      zalicz("cel1");
    });
    
    $(".cel2").mouseenter(function()
    {
      zalicz("cel2");
    });
    
    $(".cel3").mouseenter(function()
    {
      zalicz("cel3");
    });
    
    $(".cel4").mouseenter(function()
    {
      zalicz("cel4");
    });

    $(".cel5").mouseenter(function()
    {
      zalicz("cel5");
    });
    
    
    
    function random()
    {
        rand1 = Math.floor((Math.random() * 35) + 35);
        rand2 = Math.floor((Math.random() * 10) + 20);
        $("#cel1").css('bottom', rand1+"%");
        $("#cel1").css('left', rand2+"%");
        
        rand1 = Math.floor((Math.random() * 25) + 35);
        rand2 = Math.floor((Math.random() * 10) + 65);
        $("#cel2").css('bottom', rand1+"%");
        $("#cel2").css('left', rand2+"%");
        
        rand1 = Math.floor((Math.random() * 15) + 20);
        rand2 = Math.floor((Math.random() * 20) + 40);
        $("#cel3").css('bottom', rand1+"%");
        $("#cel3").css('left', rand2+"%");
        
        rand1 = Math.floor((Math.random() * 10) + 75);
        rand2 = Math.floor((Math.random() * 10) + 60);
        $("#cel4").css('bottom', rand1+"%");
        $("#cel4").css('left', rand2+"%");
        
        rand1 = Math.floor((Math.random() * 7) + 82);
        rand2 = Math.floor((Math.random() * 15) + 35);
        $("#cel5").css('bottom', rand1+"%");
        $("#cel5").css('left', rand2+"%");
    }
    
    
    function czas_start() {
        if (zaliczone < 5 && !start) {
            start = true;
            timer = setInterval(function () {
                czas = $("#wynik").html();                
                czas = parseInt(czas);
                czas++;
                $("#wynik").html(""+czas);
            }, 1000);
        }
    }
    function czas_stop() {
        if (flaga) {
            zaliczone++;
            console.log(zaliczone);
            flaga = false;
            if (zaliczone == 5) {
                element = document.createElement("LI");
                element.innerHTML = $("#wynik").html() + "s";
                $("#wyniki").append(element);
                $("#wynik").html(0);
                for (i = 1; i <= 5; i++) {
                    tmp = ".cel" + i;
                    $(tmp).css('background-color', 'aliceblue');
                }
                clearInterval(timer);
                zaliczone = 0;
                random();
                flaga = false;
                start = false;
            }
        }
    }
    function zalicz(id) {
        kolor = $("."+id).css('background-color');
        if (kolor == "rgb(255, 0, 0)" && !flaga && start) {
            tmp = $("#wynik").html();
            tmp = parseInt(tmp);
            tmp += 3;
            $("#wynik").html(tmp);
            return;
        }
        if (!flaga && start) {
            $("."+id).css('background-color', 'red');
            flaga = true;
        }
    }
});
