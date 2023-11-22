const express = require("express");
const cors = require("cors");
const dotenv = require("dotenv");
const app = express();
const http = require("http");
const { Server } = require("socket.io");

app.use(cors());
dotenv.config();

app.get("/", (req, res) => {
  res.send("sunucu ayakta");
});

const server = http.createServer(app);

server.listen(3001, () => {
  console.log("listening on *:3001 WEP");
});

const io = new Server(server, {
  cors: {
    origin: "*",
    methods: ["GET", "POST"],
  },
});

const socketIO = require("./socketIO");

io.on("connection", socketIO);


