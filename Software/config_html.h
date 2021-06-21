// config.html file in raw data format for PROGMEM
//
const char config_html[] PROGMEM = R"=====(
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
   <li><a class="pull-left active" href="/setup.html">Setup</a></li>
   <li><a class="pull-left" href="/about.html">Over</a></li>
  </ul>
  <br><br><br>
  <center>
   <h1>** Smartmeter P1 **</h1>
   <p>U kan de configuratie hier aanpassen.<br> <i>Bedenk wel dat de aanpassingen maar effectief zijn na het herstarten van het apparaat.</i>
   </p>
    <div class="config">
    <table style="width:600px">
    
<tr>
  <td class="config">
      <label><big>Hostnaam : </big></label>
      
  </td>
  <td>
      <input class="config" type="text" size="32" id="HostName" placeholder="Hostname">
  </td>
</tr>

<tr>
  <td class="config">
     <label for="HF"><big>Setup user :</big></label>
  </td>
  <td>
     <input class="config" type="text" id="www-user" placeholder="Setup user">
  </td>
</tr>
<tr>
  <td class="config">
     <label for="HF"><big>Setup password :</big></label>
  </td>
  <td>
     <input class="config" type="password" id="www-pass" placeholder="Setup password">
  </td>
</tr>

<tr>
  <td class="config">
     <label><big>MQTT server :</big></label>
  </td>
  <td>
     <input class="config" type="text" id="MQTTServ" placeholder="MQTT server">
  </td>
</tr>
<tr>
  <td class="config">
      <label for="LA"><big>MQTT port : </big></label>
  </td>
  <td>
      <input class="config" type="text" id="MQTTPort" placeholder="1883">
  </td>
</tr>
<tr>
  <td class="config">
      <label for="LA"><big>MQTT user : </big></label>
  </td>
  <td>
      <input class="config" type="text" id="MQTTUsr" placeholder="MQTT user">
  </td>
</tr>
<tr>
  <td class="config">
     <label for="HF"><big>MQTT password :</big></label>
  </td>
  <td>
     <input class="config" type="password" id="MQTTPass" placeholder="MQTT password">
  </td>
</tr>
<tr>
  <td class="config">
     <label for="HF"><big>MQTT fingerprint :</big></label>
  </td>
  <td>
     <input class="config" type="text" id="MQTTfinger" placeholder="MQTT fingerprint">
  </td>
</tr>
<tr>
  <td class="config">
     <label for="HF"><big>MQTT topic :</big></label>
  </td>
  <td>
     <input class="config" type="text" id="MQTTTopic" placeholder="energy/p1">
  </td>
</tr>
<tr>
  <td class="config">
     <label for="HF"><big>Delay :</big></label>
  </td>
  <td>
     <input class="config" type="number" min="1" max="99999" size="40" id="Delay" placeholder="Delay">
  </td>
</tr>
</table>
</div>
 <br><input class="config" type="text" id="resultstr" placeholder="Waiting for input...." readonly>
 <br><br>
   <button class="button" onclick="savePref()">Save</button>
   &nbsp;&nbsp;
   <button class="button buttonr" onclick="httpGet('reset')">Restart</button>
   &nbsp;&nbsp;
   <button class="button buttonr" onclick="location.href = '/update.html';">Update</button>
   &nbsp;&nbsp;
   <button class="button" onclick="httpGet('getdefs')">Default</button>

    <script>

    // Save the preferences
   function savePref()
   {
     var str ="";
     var tstr1; //tempstring
     var tstr2; //tempstring
     var theUrl = "data/?saveprefs&version=" + Math.random() ;
     var xhr = new XMLHttpRequest() ;
     xhr.onreadystatechange = function()
        {
          if ( xhr.readyState == XMLHttpRequest.DONE )
          {
            resultstr.value = xhr.responseText ;
          }
        }
     tstr2=document.getElementById("HostName").value;
     if (tstr2.length>0) {
      tstr1="HostName=";
      str=str+tstr1+tstr2; 
     }
     tstr2=document.getElementById("MQTTServ").value;
     tstr1="MQTTServ=";
     if (str.length>0) str=str+"&";
     str=str+tstr1+tstr2; 
     tstr2=document.getElementById("MQTTPort").value;
     if (tstr2.length>0) {
      str=str+"&";
      tstr1="MQTTPort=";
      str=str+tstr1+tstr2; 
     }
     tstr2=document.getElementById("MQTTUsr").value;
     str=str+"&";
     tstr1="MQTTUsr=";
     str=str+tstr1+tstr2; 
     tstr2=document.getElementById("MQTTPass").value;
     str=str+"&";
     tstr1="MQTTPass=";
     str=str+tstr1+tstr2;
     tstr2=document.getElementById("MQTTfinger").value;
     str=str+"&";
     tstr1="MQTTfinger=";
     str=str+tstr1+tstr2; 
     tstr2=document.getElementById("MQTTTopic").value;
     if (tstr2.length>0) {
      str=str+"&";
      tstr1="MQTTTopic=";
      str=str+tstr1+tstr2; 
     }
     tstr2=document.getElementById("Delay").value;
     if (tstr2.length>0) {
      str=str+"&";
      tstr1="Delay=";
      str=str+tstr1+tstr2; 
     }

     tstr2=document.getElementById("www-user").value;
     if (tstr2.length>0) {
      str=str+"&";
      tstr1="www-user=";
      str=str+tstr1+tstr2; 
     }

     tstr2=document.getElementById("www-pass").value;
     if (tstr2.length>0) {
      str=str+"&";
      tstr1="www-pass=";
      str=str+tstr1+tstr2; 
     }

    while (str.indexOf(" ")>= 0)
       {
         str=str.replace(" ","")      
       }
     xhr.open("POST",theUrl,true) ;
     xhr.setRequestHeader("Content-type","application/x-www-form-urlencoded") ;
     xhr.send(str) ;
    }

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

   // Fill configuration
   var i, sel, opt, lines, parts ;
   var theUrl = "data/?config" + "&version=" + Math.random() ;
   var xhr = new XMLHttpRequest() ;
   xhr.onreadystatechange = function() {
     if ( xhr.readyState == XMLHttpRequest.DONE )
     {
       lines = xhr.responseText.split ( " " ) ;
       for ( i = 0 ; i < (lines.length) ; i++ )
       {
         parts = lines[i].split ( "=" ) ;
         document.getElementById(parts[0]).value = parts[1];
       }
     }
   }
   xhr.open ( "GET", theUrl, false ) ;
   xhr.send() ;
   </script>
  </body>
</html>
)=====" ;
