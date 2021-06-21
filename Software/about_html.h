// about.html file in raw data format for PROGMEM
//
const char about_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <title>About Smartmeter P1</title>
  <meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
  <meta name="viewport" content="width=device-width, initial-scale=1.0"> 
<link rel="Shortcut Icon" type="image/ico" href="favicon.ico">
  <link rel="stylesheet" type="text/css" href="smartmeter.css">
 </head>
 <body>
  <ul>
   <li><a class="pull-left" href="#">Smartmeter P1</a></li>
   <li><a class="pull-left" href="/index.html">Data</a></li>
   <li><a class="pull-left" href="/setup.html">Setup</a></li>
   <li><a class="pull-left active" href="/about.html">Over</a></li>
  </ul>
  <br><br><br>
  <center>
   <h1>** Smartmeter P1 **</h1>
  <p>Uitlezen van de Vlaamse "slimme energiemeter" via de P1-poort.<br>
	<p>Auteur: Koenraad Lelong<br>
	Datum : mei 2020</p>
  Gebaseerd op verschillende idee&euml;n op Github :<br>
   <a href="https://github.com/neographikal/P1-Meter-ESP8266-MQTT" target="_blank" name="neographical" title="title">neographical</a><br>
  en anderen<br>
  </center>
 </body>
</html>
)=====" ;
