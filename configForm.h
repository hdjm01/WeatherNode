const char configForm[] PROGMEM = R"(
 <form method="post">
 
  <fieldset>
   <legend>MQTT</legend>  
   <p>
    <label for="mqtt_topic">Topic: </label>
    <input type="text" id="mqtt_topic" name="mqtt_topic"/>
   </p>
   <p>
    <label for="mqtt_client">Client Name: </label>
    <input type="text" id="mqtt_client" name="mqtt_client"/>
   </p>
   <p>
    <label for="mqtt_server">Host: </label>
    <input type="text" id="mqtt_server" name="mqtt_server"/>
   </p>
   <p>
    <label for="mqtt_port">Port: </label>
    <input type="text" id="mqtt_port" name="mqtt_port" size="6"/>
   </p>
   <p>
    <label for="mqtt_enabled">Enable: </label>
    <input type="checkbox" id="mqtt_enabled" name="mqtt_enabled"/>
   </p>
   <fieldset>
   <legend>MQTT User</legend>
   <p>
    <label for="mqtt_username">User: </label>
    <input type="text" id="mqtt_username" name="mqtt_username" size="16" />
   </p>
   <p>
    <label for="mqtt_update_pw">Password: </label>
    <input type="mqtt_password" id="mqtt_update_pw" name="mqtt_update_pw" size="16" />
   </p>
  </fieldset>
   <input type="button" value="Test" onclick="testMQTT();" id="mqtt_test"/>
  </fieldset>
  
  <fieldset>
   <legend>User</legend>
   <p>
    <label for="username">User: </label>
    <input type="text" id="username" name="username" size="16" />
   </p>
   <p>
    <label for="update_pw">Password: </label>
    <input type="password" id="update_pw" name="update_pw" size="16"  />
   </p>
  </fieldset>
  <fieldset>   
   <legend><p>I²C Setup</p></legend>
   <p class="notation">Attention!</p>
   <p>
     <label for="i2c_address">Address: </label>
     <input type="text" id="i2c_address" name="i2c_address" enable="false" value="0x77" size="5" />
   </p>
   <p>
     <label for="i2c_scl">Pin für scl: </label>
     <input type="number" id="i2c_scl" name="i2c_scl" size="3"  min="3" max="16"/>
   </p>  
   <p>
    <label for="i2c_sda">Pin für sda: </label>
    <input type="number" id="i2c_sda" name="i2c_sda" size="3" min="3" max="16"/>
   </p>
   <p>
    <label for="i2c_enabled">Enable: </label>
    <input type="checkbox" id="i2c_enabled" name="i2c_enabled"/>
   </p>
  </fieldset>
  <div>
   <input type="button" value="Save" onclick="setCFG();" />
  <div>
 </form>
)";
