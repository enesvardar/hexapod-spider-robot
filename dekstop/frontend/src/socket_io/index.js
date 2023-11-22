import React, { useEffect, useRef } from "react";
import { io } from "socket.io-client";
import { useDispatch, useSelector } from "react-redux";

export const SocketIO = () => {
  const command = useSelector((state) => state.socketIO.command); // her bir bacağın açı bilgilerini tutan data
  const dispatch = useDispatch();
  const socket = useRef();

  useEffect(() => {
    socket.current = io("http://localhost:3001/");
  }, []);

  useEffect(() => {
    socket.current.emit("command", command);
  }, [command]);

  return <div></div>;
};
