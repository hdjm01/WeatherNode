#pragma once

const char INDEX[] PROGMEM = R"(
<html>
 <head>
  <meta charset="UTF-8">
  <title>WeatherNode</title>
  <link rel="stylesheet" type="text/css" href="./main.css">
  <script src="/main.js"></script>
 </head>
 <body>
  <h1>
   <a href="/">WeatherNode</a>
  </h1>
  <ul class="navi">
   <li onclick="configForm();">Config</li>
   <li><a href="/firmware">Update</a></li>
  </ul>
  <div id="main">
   Wireless Weather Telemerie Device
  </div>
  <div id="footer">
  <p id="projectLink">
   <a href="https://github.com/hdjm01/WeatherNode" target="_blank">Project Website</a>
  </p>  
  </div>
 </body>
</html>
)";
