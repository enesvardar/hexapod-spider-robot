const mqtt = require("mqtt");

const client = mqtt.connect(
  `mqtt://${process.env.MQTT_HOST}:${process.env.MQTT_PORT}`,
  {
    clientId: process.env.MQTT_CLIENT_ID,
    clean: true,
    connectTimeout: 4000,
    username: "emqx",
    password: "public",
    reconnectPeriod: 1000,
  }
);

client.on("connect", () => {
  console.log("Connected MQTT");

  client.subscribe([process.env.MQTT_TOPIC_NODE]);

  client.publish(process.env.MQTT_TOPIC_ESP, "Hello Esp32", {
    qos: 0,
    retain: false,
  });
});


module.exports = client;
