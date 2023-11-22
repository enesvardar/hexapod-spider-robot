import React from "react";
import { useDispatch } from "react-redux";
import { socket_emit } from "../../redux/socketio/socketSlice";

export const Butttons = () => {

  const dispatch = useDispatch()

  const handleMouseDown = (direction) => {
    dispatch(socket_emit(direction))
  };

  const handleMouseUp = (e) => {
    dispatch(socket_emit("stop"))
  };

  const reset = () => {
    handleMouseDown("reset");
    setTimeout(()=>{window.location.reload(false);}, 1000);
  }

  return (

    <div className="butttons">
      <div className="group">
      <button className="button" onClick={() => {dispatch(socket_emit("balance"))}}>
          <img src="balance.png"></img>
        </button>
        <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => handleMouseDown("forw")} >
          <img src="forward.png"></img>                                                           
        </button>
        <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => handleMouseDown("flash")} >
          <img src="flash.png"></img>                                                           
        </button>
      </div>
      <div className="group">
        <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => handleMouseDown("left")} >
          <img src="left.png"></img>
        </button>
        <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => handleMouseDown("rote")} >
          <img src="rotate.png"></img>
        </button>
        <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => handleMouseDown("rigt")} >
          <img src="right.png"></img>
        </button>
      </div>
      <div className="group">
      <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => handleMouseDown("dance")} >
          <img src="dance.png"></img>
        </button>
        <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => handleMouseDown("back")} >
          <img src="backwards.png"></img>
        </button>
        <button className="button" onMouseUp={handleMouseUp} onMouseDown={() => reset()} >
          <img src="reset.png"></img>
        </button>
      </div>
    </div>

  );
};
