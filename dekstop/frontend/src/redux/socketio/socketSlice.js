import { createSlice } from "@reduxjs/toolkit";

export const socketIOSlice = createSlice({
  name: "socketIO",
  initialState: {
    // io:io("http://localhost:3001/")
    command: "",
  },
  reducers: {
    socket_emit: (state, action) => {
      state.command = action.payload;
    },
  },
});

// Action creators are generated for each case reducer function
export const { socket_emit } = socketIOSlice.actions;

export default socketIOSlice.reducer;
