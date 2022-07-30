#pragma once

const char JS[] PROGMEM = R"(

  var status_time = 5000;
  var status_init_time = 2000;

  function checkStatus(){
    console.log("check Status");

      var request = new XMLHttpRequest();
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
             document.getElementById("status").style.fill = "green";
           }else{
            document.getElementById("status").style.fill = "red";
           }
         }
       }
       request.open("GET", "test", true);
       request.send(null);
    
    window.setTimeout(checkStatus, status_time);
  }

  function checkStatusRegister(){
    window.setTimeout(checkStatus, status_init_time);
  }

   function configForm(){
       var request = new XMLHttpRequest();
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
             document.getElementById("main").innerHTML = this.responseText;
             getCFG();
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

   function testMQTT(){
       var btn = document.getElementById("mqtt_test");
       var request = new XMLHttpRequest();
       const formElement = document.querySelector("form");
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
             btn.style.backgroundColor = "green";
           }else{
             btn.style.backgroundColor = "red";
           }
         }
       }
       request.open("GET", "mqtt", true);
       try{
        request.send(null); 
       }catch(e){
        alert("Fehler" + e);
       }
       
    
   }

   function getCFG(){
       var request = new XMLHttpRequest();
       request.onreadystatechange = function(){
         if (this.readyState == 4) {
           if (this.status == 200) {
            var xmlDoc = this.responseXML;

            var mapping = ["mqtt_server","mqtt_port", "mqtt_client", "mqtt_topic", "username", "i2c_sda", "i2c_scl"];
            
            var arrayLength = mapping.length;
            
            for (var i = 0; i < arrayLength; i++) {
              console.log(mapping[i]);
              //Do something
              
              if(document.getElementById(mapping[i]) && xmlDoc.getElementById(mapping[i]))
              {
               document.getElementById(mapping[i]).value = xmlDoc.getElementById(mapping[i]).textContent;
              }
            }

           }
         }
       }
       request.open("GET", "config.xml", true);
       request.send(null);
   }
  
  )";
