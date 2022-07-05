WeatherNode
=============================================================================

Environment Parameter Device (Temp, ...)

https://github.com/hdjm01/WeatherNode


Usage
----------------------------------------------------------------------------

Get Data of BME280 Sensor on Serial or via Http as JSON.


Setup
----------------------------------------------------------------------------

Since implementation of WiFiManager the Device starts with an Access Point "WeatherNode" and keyword "setupkw39"


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
	

Http
-----------------------------------------------------------------------------
http://ip/json

Returns JSON with current data


ReleaseNotes/RevHistory
-----------------------------------------------------------------------------

* 01.07.22	BME280 https://github.com/hdjm01/WeatherNode/issues/3
* 01.07.22	JSON https://github.com/hdjm01/WeatherNode/issues/1
* 30.06.22	Webserver https://github.com/hdjm01/WeatherNode/issues/4
* 30.06.22 	WifiManager https://github.com/hdjm01/WeatherNode/issues/2