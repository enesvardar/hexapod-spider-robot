import "./App.css";
import React from "react";
import { Butttons } from "./components/buttons/index";
import { Sliders } from "./components/sliders";
import { SocketIO } from "./socket_io";

function App() {
  return (
    <div className="App">
      <SocketIO/>
      <div className="container">
        <div className="controlGroup">
          <Sliders />
          <Butttons />
        </div>
      </div>
    </div>
  );
}

export default App;
