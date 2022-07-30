const char configForm[] PROGMEM = R"(
 <form method="post">
  <fieldset>
   <legend>MQTT</legend>  
   <p>
    <label for="mqtt_host">Host: </label>
    <input type="text" id="mqtt_host" name="mqtt_host"/>
   </p>
   <p>
    <label for="mqtt_port">Port: </label>
    <input type="text" id="mqtt_port" name="mqtt_port" size="6"/>
   </p>
  </fieldset>
  <fieldset>
   <legend>User</legend>
   <p>
    <label for="username">User: </label>
    <input type="text" id="username" name="username" size="10" />
   </p>
   <p>
    <label for="update_pw">Password: </label>
    <input type="password" id="update_pw" name="update_pw" />
   </p>
  </fieldset>
  <fieldset>   
   <legend><p>I²C Setup</p></legend>
   <p>
     <label for="i2c_scl">Pin für scl: </label>
     <input type="text" id="i2c_scl" name="i2c_scl" size="3"/>
   </p>  
   <p>
    <label for="i2c_sda">Pin für sda: </label>
    <input type="text" id="i2c_sda" name="i2c_sda" size="3"/>
   </p>
  </fieldset>
  <input type="submit" name="action" value="Save"/>
  <input type="button" value="Load" onclick="getCFG();"/>
 </form>
)";
