#pragma once

const char JS[] PROGMEM = R"(
   function configForm(){
       var request = new XMLHttpRequest();
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
             document.getElementById("main").innerHTML = this.responseText;
           }
         }
       }
       request.open("GET", "config", true);
       request.send(null);
   }

   function getCFG(){
       var request = new XMLHttpRequest();
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
            var xmlDoc = this.responseXML;
            
            document.getElementById("mqtt_host").value = xmlDoc.getElementById("mqtt_host").nodeValue;
            document.getElementById("mqtt_port").value = xmlDoc.getElementById("mqtt_port").nodeValue;

            document.getElementById("username").value = xmlDoc.getElementById("username").nodeValue;

            document.getElementById("i2c_sda").value = xmlDoc.getElementById("sda_pin").nodeValue;
            document.getElementById("main").innerHTML = xmlDoc.getElementById("scl_pin").nodeValue;

           }
         }
       }
       request.open("GET", "getcfg", true);
       request.send(null);
   }
  
  )";
