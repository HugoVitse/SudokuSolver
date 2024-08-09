import React, { useEffect, useState } from "react";
import Webcam from "react-webcam";
import square from './square.png'

const videoConstraints = {
  facingMode: "forward",
};

const Scanner = () => {
  const[imgsrc,setimgsrc] = useState()
  const webcamRef = React.useRef(null);
  useEffect(()=>{
    setInterval(() => {
        capture()
    }, 1000);
  },[])
  const capture = React.useCallback(
    () => {
      const imageSrc = webcamRef.current.getScreenshot();
      setimgsrc(imageSrc)
    },
    [webcamRef]
  );
  return (
    <div>
      <Webcam
        audio={false}
        ref={webcamRef}
        screenshotFormat="image/jpeg"
        top={0}
        left={0}
        width={window.innerWidth}
        height={window.innerHeight}
        style={{position:'absolute',top:0,left:0}}
        videoConstraints={videoConstraints}
      />
      <img style={{position:'absolute',top:0,width:"100%"}} src={square}/>

      <img src={imgsrc}></img>
    </div>
  );
};

export default Scanner