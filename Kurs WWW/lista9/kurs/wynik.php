<?php
    $conn = new mysqli('localhost', 'root', '', 'filmy');
    if ($conn->connect_error)
        die("Connection failed: " . $conn->connect_error);
        $conn -> query ('SET NAMES utf8');
        $conn -> query ('SET CHARACTER_SET utf8_unicode_ci');
        
        $tytul = $_REQUEST['tytul'];
        if($tytul!='')
        {
            $sql = "SELECT tytul FROM film where tytul like '$tytul%' order by tytul ASC limit 10";
            $result = $conn->query($sql);
            
            if ($result->num_rows > 0)
            {
                // output data of each row
                while($row = $result->fetch_assoc())
                {
                    echo $row["tytul"];
                    echo "<br>";
                }
            }
        }
?>