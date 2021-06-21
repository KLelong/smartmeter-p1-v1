// config.html file in raw data format for PROGMEM
//
const char update_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <title>Smartmeter P1 config</title>
  <meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
  <meta name="viewport" content="width=device-width, initial-scale=1.0"> 
  <link rel="stylesheet" type="text/css" href="smartmeter.css">
  <link rel="Shortcut Icon" type="image/ico" href="favicon.ico">
 </head>
 <body>
  <ul>
   <li><a class="pull-left" href="#">Smartmeter P1</a></li>
   <li><a class="pull-left" href="/index.html">Data</a></li>
   <li><a class="pull-left" href="/setup.html">Setup</a></li>
   <li><a class="pull-left" href="/about.html">Over</a></li>
  </ul>
  <br><br><br>
  <center>
   <h1>** Smartmeter P1 **</h1>
   <p>Kies het firmware-bestand...<br><i>Na een succesvolle upload zal het apparaat opnieuw opstarten.</i>
   </p>
    <div class="config">
    </div>
 <form method='POST' action='/upload' enctype='multipart/form-data'>
 <input type='file' name='update'><br>
 <input class="button buttonr" type='submit' value='Update'>
 </form>
 </body>
</html>
)=====" ;
