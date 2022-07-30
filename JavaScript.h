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

   function setCFG(){
       var request = new XMLHttpRequest();
       const formElement = document.querySelector("form");
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
            alert("Die Änderungen wurden gespeichert");
           }
         }
       }
       request.open("POST", "setcfg", true);
       request.send(new FormData(formElement));
   }

   function getCFG(){
       var request = new XMLHttpRequest();
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
            var xmlDoc = this.responseXML;
            
            document.getElementById("mqtt_server").value = xmlDoc.getElementById("mqtt_server").textContent;
            document.getElementById("mqtt_port").value = xmlDoc.getElementById("mqtt_port").textContent;

            document.getElementById("username").value = xmlDoc.getElementById("username").textContent;

            document.getElementById("i2c_sda").value = xmlDoc.getElementById("sda_pin").textContent;
            document.getElementById("i2c_scl").value = xmlDoc.getElementById("scl_pin").textContent;

           }
         }
       }
       request.open("GET", "getcfg", true);
       request.send(null);
   }
  
  )";
