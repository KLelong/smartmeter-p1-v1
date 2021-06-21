// index.html file in raw data format for PROGMEM
//
const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <title>Smartmeter P1</title>
  <meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
  <meta name="viewport" content="width=device-width, initial-scale=1.0"> 
  <link rel="stylesheet" type="text/css" href="smartmeter.css">
  <link rel="Shortcut Icon" type="image/ico" href="favicon.ico">
 </head>
 <body>
  <ul>
   <li><a class="pull-left" href="#">Smartmeter P1</a></li>
   <li><a class="pull-left active" href="index.html">Data</a></li>
   <li><a class="pull-left" href="setup.html">Setup</a></li>
   <li><a class="pull-left" href="about.html">Over</a></li>
  </ul>
  <br><br><br>
  <center>
   <h1>** Smartmeter P1 **</h1>
   <label><big>Versie : </big></label>
   <input class="Version" type="text" size="4" id="Version" placeholder="Versie" readonly>
   <br>
   <label>WiFi signaal : </label>
   <input class="Version" type="text" size="4" id="rssi" placeholder="WiFi signaal" readonly>
   <br><br>
   <div style="overflow-x:auto;">
   <table style="width:600px">
    <tr>
     <td><center>
      <label for="HA"><big>Energie verbruik tarief 1: </big></label>
      <br>
      <input type="text" size="10" id="ConsDay" placeholder="cons tarief 1..." readonly> Wh
     </td>
     <td><center>
      <label for="HF"><big>Energie verbruik tarief 2: </big></label>
      <br>
      <input type="text" size="10" id="ConsNight" placeholder="cons tarief 2..." readonly> Wh
     </center></td>
    </tr>
    <tr>
     <td><center>
      <label for="LA"><big>Energie productie tarief 1: </big></label>
      <br>
      <input type="text" size="10" id="ProdDay" placeholder="prod tarief 1..." readonly> Wh
     </td>
     <td><center>
      <label for="LF"><big>Energie productie tarief 2: </big></label>
      <br>
      <input type="text" size="10" id="ProdNight" placeholder="prod tarief 2..." readonly> Wh
     </center></td>
    </tr>
    <tr>
     <td><center>
      <label for="LA"><big>Energie verbruik nu: </big></label>
      <br>
      <input type="text" size="10" id="ConsNow" placeholder="cons nu..." readonly> W
     </td>
     <td><center>
      <label for="LF"><big>Energie productie nu: </big></label>
      <br>
      <input type="text" size="10" id="ProdNow" placeholder="prod nu..." readonly> W
     </center></td>
    </tr>
    <tr>
     <td><center>
      <label for="LA"><big>Gas verbruik: </big></label>
      <br>
      <input type="text" size="10" id="ConsGas" placeholder="cons gas..." readonly> m&sup3
     </td>
    </tr>
   </table>
   </div>
  </center>
   <script>
   function httpGet ( theReq )
   {
    var theUrl = "data/?" + theReq + "&version=" + Math.random() ;
    var xhr = new XMLHttpRequest() ;
    xhr.onreadystatechange = function() {
      if ( xhr.readyState == XMLHttpRequest.DONE )
      {
        resultstr.value = xhr.responseText ;
      }
    }
    xhr.open ( "GET", theUrl ) ;
    xhr.send() ;
   }

   var i, lines, parts, delayVal;

   function getData() {

    var theUrl = "data/?data" + "&version=" + Math.random() ;
    var xhr = new XMLHttpRequest() ;
    xhr.onreadystatechange = function() {
     lines = xhr.responseText.split ( " " ) ;
     for ( i = 0 ; i < (lines.length) ; i++ )
     {
       parts = lines[i].split ( "=" ) ;
       if (parts[0]=="Delay") {}
       else
          document.getElementById(parts[0]).value = parts[1];
       }
//       setTimeout("getData()",delayVal);
   }
    xhr.open ( "GET", theUrl ) ;
    xhr.send() ;
   }

   var theUrl = "data/?data" + "&version=" + Math.random() ;
   var xhr = new XMLHttpRequest() ;
   xhr.onreadystatechange = function() {
     if ( xhr.readyState == XMLHttpRequest.DONE ) {
       lines = xhr.responseText.split ( " " ) ;
       for ( i = 0 ; i < (lines.length) ; i++ ) {
         parts = lines[i].split ( "=" ) ;
         if (parts[0]=="Delay") {
            delayVal=parts[1]*1000;
            setInterval("getData()",delayVal);
         }
         else
            document.getElementById(parts[0]).value = parts[1];
       }
     }
   }
   xhr.open ("GET", theUrl, false);
   xhr.send();
  </script>
 </body>
</html>
<noscript>
  <link rel="stylesheet" href="smartmeter.css">
  Sorry, Smartmeter P1 does not work without JavaScript!
</noscript>
)=====" ;
