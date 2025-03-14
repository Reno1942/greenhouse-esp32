# MQTT Topics & Config
### Topic layout : category / category_id / component / component_id / property

### States :

| Topic | Payload |
|-------|---------|
| greenhouse/greenhouse_reno/relay/top_light/state | boolean |
| greenhouse/greenhouse_reno/relay/bottom_light/state | boolean |
| greenhouse/greenhouse_reno/relay/fan/state | boolean |
| greenhouse/greenhouse_reno/relay/pump/state | boolean |
| greenhouse/greenhouse_reno/sensor/dht/state | {float, float} |
| greenhouse/greenhouse_reno/sensor/tank_percentage/state | int |
| greenhouse/greenhouse_reno/config/light_on_time/state | int |
| greenhouse/greenhouse_reno/config/light_off_time/state | int |
| greenhouse/greenhouse_reno/mode/auto/state | boolean |

### Command : 
| Topic | Payload |
|-------|---------|
| greenhouse/greenhouse_reno/relay/top_light/command | boolean |
| greenhouse/greenhouse_reno/relay/bottom_light/command | boolean |
| greenhouse/greenhouse_reno/relay/fan/command | boolean |
| greenhouse/greenhouse_reno/relay/pump/command | boolean |
| greenhouse/greenhouse_reno/config/light_on_time/command | int |
| greenhouse/greenhouse_reno/config/light_off_time/command | int |
| greenhouse/greenhouse_reno/mode/auto/command | boolean |

### Alerts :
| Topic | Payload |
| ----- | ------- |
| greenhouse/greenhouse_reno/alert/water_level_low/state | empty |
| greenhouse/greenhouse_reno/alert/water_level_critical/state | empty |
| greenhouse/greenhouse_reno/alert/component_disconnected/state | string |