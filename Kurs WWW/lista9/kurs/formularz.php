<html>
    <head>
        <title>Kurs WWW - Kamil Woś</title>
        <meta charset="UTF-8">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
        <script>
            function test(){
                    var tmp_login = $("#login").val();
                    var tmp_haslo1 = $("#haslo1").val();
                    var tmp_haslo2 = $("#haslo2").val();
                    var tmp_data = $("#data").val();
                    $.post("ajax.php",
                    {
                        login: tmp_login,
                        haslo1: tmp_haslo1,
                        haslo2: tmp_haslo2,
                        data: tmp_data
                    },
                    function(data, status)
                    {
                        if(data)
                            $(".error").html(data);
                        else
                        {
                            $(".error").html(' ');
                        }
                    });
                
            }
        </script>
    </head>
    <body>
            <input type="text" name="login" id="login" placeholder="Login">
            <input type="password" name="haslo1" id="haslo1"  placeholder="Hasło">
            <input type="password" name="haslo2" id="haslo2"  placeholder="Powtórz hasło">
            <input type="date" name="data" id="data" placeholder="Data urodzenia">
            <input type="submit" name="wyslij" id="wyslij" onclick="test();" value="Wyślij">
        
        <div class="error"></div>
    </body>
</html>