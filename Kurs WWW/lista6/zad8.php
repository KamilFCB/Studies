<?php
$name = 'alaaaa';
$value = 'koooot';
$expirationTime = 100;    // Session cookie.
$path = '/';
$domain = 'http://kamilwos.azurewebsites.net';
$isSecure = false;
$isHttpOnly = false;
setcookie($name, $value, $expirationTime, $path, $domain, $isSecure, $isHttpOnly);
?>

<span id="myId"><span>
<script>
function listCookies()
{
    var cookies = document.cookie.split(';');
    var res = '';
    for (var i = 1 ; i <= cookies.length; i++)
        res += i + ' ' + cookies[i-1] + "\n";

    return res;
}

function getCookie(cname) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}

function setCookie(cname, cvalue, exdays)
{
    var d = new Date();
    d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
    var expires = "expires="+d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

setCookie('ala', 'kot', 1);

document.getElementById('myId').innerHTML=listCookies();

</script>