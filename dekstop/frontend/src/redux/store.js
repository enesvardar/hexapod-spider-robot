import { configureStore } from "@reduxjs/toolkit";
import socketIOReducer from "./socketio/socketSlice";

export default configureStore({
  reducer: {
    socketIO: socketIOReducer,
  },
});
