import { useEffect } from "react";
import axiosClient from "../axiosClient";

export default function AHome() {
  useEffect(()=>{
  axiosClient.get("/holded-accounts")
  .then(response=>console.log(response.data));

  },[])

  return (
    <div>
      <h1 className="text-2xl font-bold">Admin Home</h1>
      
    </div>
  );
}