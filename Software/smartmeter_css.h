// smartmeter.css file in raw data format for PROGMEM
//
const char smartmeter_css[] PROGMEM = R"=====(
body {
   background-color: lightsalmon;
   font-family: Arial, Helvetica, sans-serif;
}

h1 {
   color: navy;
   margin-left: 20px;
   font-size: 150%
}

ul {
   list-style-type: none;
   margin: 0;
   margin-left: -10px;
   overflow: hidden;
   background-color: saddlebrown;
   position:fixed;
   top:0;
   width:100%;
   z-index:100;
}

li .pull-left {
   float: left;
}

li .pull-right {
   float: right;
}

li a {
   display: block;
   color: white;
   text-align: center;
   padding: 14px 16px;
   text-decoration: none;
}

li a:hover, a.active {
   background-color: #111;
}

td.config {
   text-align: right;
}

.button {
   width: 90px;
   height: 30px;
   background-color: #128F76;
   border: none;
   color: white;
   text-align: center;
   text-decoration: none;
   display: inline-block;
   font-size: 16px;
   margin: 4px 2px;
   cursor: pointer;
   border-radius: 10px;
}

.buttonr {background-color: red;}

.select {
   width: 160px;
   height: 32px;
   padding: 5px;
   background: white;
   font-size: 16px;
   line-height: 1;
   border: 1;
   border-radius: 5px;
   -webkit-border-radius: 5px;
   -moz-border-radius: 5px;
   -webkit-appearance: none;
   border: 1px solid black;
   border-radius: 10px;
}

.selectw {width: 410px;}

input {
   margin: 0;
   height: 28px;
   background: white;
   font-size: 16px;
   appearance: none;
   box-shadow: none;
   border-radius: 5px;
   -webkit-border-radius: 5px;
   -moz-border-radius: 5px;
   -webkit-appearance: none;
   border: 1px solid black;
   border-radius: 10px;
}

input[type="text"] {
   text-align: right;
}

input.config {
   text-align: left;
   width: 300px;
}

input.Version {
   text-align: center;
   border: 0px;
   background-color: transparent;
}

input[type="text"]:focus {
  outline: none;
}

input[type=submit] {
  width: 200px;
  height: 40px;
  background-color: #128F76;
  border: none;
  color: white;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
  border-radius: 5px;
}

textarea {
  width: 80;
  height: 25;
  border: 1px solid black;
  border-radius: 10px;
  padding: 5px;
  font-family: Courier, "Lucida Console", monospace;
  background-color: white;
  resize: none;
}
)=====" ;
