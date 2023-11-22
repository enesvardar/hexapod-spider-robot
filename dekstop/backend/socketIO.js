const client = require("./mqtt");

socketIO = (socket) => {
  
  console.log("kullanıcı bağlandı");

  socket.on("disconnect", () => {
    console.log("kullanıcı ayrıldı");
  });

  socket.on("command", (data) => {

    console.log(data)

    client.publish(process.env.MQTT_TOPIC_ESP, data, {
      qos: 0,
      retain: false,
    });
  });
};

module.exports = socketIO;
