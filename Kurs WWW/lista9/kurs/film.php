<html>
    <head>
        <title>Kurs WWW - Kamil Woś</title>
        <meta charset="UTF-8">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
        <script>
            function wynik(str)
            {
                if(str==='')
                    $("#res").html('');
                else
                {
                    $.ajax({url: "wynik.php", data: {'tytul': str}, success: function(result)
                    {
                        if(result)
                            $("#res").html(result);
                        else
                            $("#res").html('Brak wyników');
                    }});
                }
            }
        </script>
    </head>
    <body>
        <input type="text" placeholder="Tytuł" onkeyup="wynik(this.value);">
        <div id="res"></div>
    </body>
</html>