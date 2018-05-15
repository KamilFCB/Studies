<?php
    $login = $_POST["login"];
    $haslo1 = $_POST["haslo1"];
    $haslo2 = $_POST["haslo2"];
    $data = $_POST["data"];
    
    if($data != null)
    {
        $data_tmp = explode("-", $data);
    
        if(!checkdate($data_tmp[1], $data_tmp[2], $data_tmp[0]))
            echo "Błędna data<br>";
    }
    else
        echo "Musisz podać datę<br>";
    
    if($haslo1 != $haslo2 && $haslo1 !=null && $haslo2 != null)
        echo "Hasła nie są identyczne<br>";
    
    if($haslo1 == null || $haslo2 == null)
        echo "Musisz podać hasła<br>";
        
    if($login != null)
    {
        $login_tmp = explode(" ", $login);
        if(count($login_tmp)!=1)
            echo "Błędny login<br>";
    }
    else
        echo "Musisz podać login<br>";
        
    echo "";
?>