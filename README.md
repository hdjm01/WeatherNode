
WeatherNode
=============================================================================

Environment Parameter Device (Temp, ...)

https://github.com/hdjm01/WeatherNode


Usage
----------------------------------------------------------------------------

Get Data of BME280 Sensor on Serial or via Http as JSON.


Setup
----------------------------------------------------------------------------

### WiFi

Since implementation of [WiFiManager](https://github.com/tzapu/WiFiManager) the Device starts with an Access Point "WeatherNode" and keyword "setupkw39"

Open http://192.168.4.1 an setup your WiFi.

### MQTT

Static Server

ToDo: https://github.com/hdjm01/WeatherNode/issues/25


Serial
----------------------------------------------------------------------------

    CMD        Response
	-------------------------
    BME280     JSON
    SENSORS    JSON


JSON
----------------------------------------------------------------------------

Example

    {
    	"name": "WeatherNode",
    	"BME280": {
    		"Temperatur": {
    			"value": "29.45",
    			"unit": "°C"
    		},
    		"Luftfeuchte": {
    			" value": "35.38",
    			"unit": "%"
    		},
    		"Luftdruck": {
    			"value": "996.43",
    			"unit": "hPa"
    		}
    	}
    }


MQTT
-----------------------------------------------------------------------------

    /WeatherNode/[ID]/BME280/
		./Temperatur
			./value
			./unit
    	./Luftfeuchte
			./value
			./unit
    	./Luftdruck
			./value
			./unit
		./data/[json]

Http
-----------------------------------------------------------------------------
http://ip/json

Returns JSON with current data


ReleaseNotes/RevHistory
-----------------------------------------------------------------------------

1.0.1

* 09.07.22  Version - https://github.com/hdjm01/WeatherNode/issues/34
* 09.07.22  Update - https://github.com/hdjm01/WeatherNode/issues/10
* 09.07.22  JSON an MQTT - https://github.com/hdjm01/WeatherNode/issues/27
* 09.07.22  Link WifiManager - https://github.com/hdjm01/WeatherNode/issues/28
* 09.07.22  IP ausgeben - https://github.com/hdjm01/WeatherNode/issues/24
* 09.07.22  Chip ID in JSON - https://github.com/hdjm01/WeatherNode/issues/23
* 09.07.22  Fix JSON value - https://github.com/hdjm01/WeatherNode/issues/30
* 09.07.22  Start Page - https://github.com/hdjm01/WeatherNode/issues/17
* 05.07.22	MQTT - https://github.com/hdjm01/WeatherNode/issues/15
* 01.07.22	BME280 - https://github.com/hdjm01/WeatherNode/issues/3
* 01.07.22	JSON - https://github.com/hdjm01/WeatherNode/issues/1
* 30.06.22	Webserver - https://github.com/hdjm01/WeatherNode/issues/4
* 30.06.22 	WifiManager - https://github.com/hdjm01/WeatherNode/issues/2