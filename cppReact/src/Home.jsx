import { useNavigate } from "react-router-dom";
import { useStateContext } from "./context/ContextProvider";
import { useEffect, useState } from "react";
import axiosClient from "./axiosClient";
export default function Home() {
  const {user,token}=useStateContext();
  const navigate = useNavigate();
  const [balance,setBalance]=useState(0);
  useEffect(()=>{
  if(user&&user.nationalID=="123456789123"){
    navigate('/admin/admin-home')
  }
  },[])
  useEffect(()=>{
    axiosClient.post("/get-balance",{
      "email":user.email
    }).then(req=>{
      console.log(req);
      setBalance(req.data.balance);
    })
  },[])
  
  console.log(user);
  return (
    
    <div>
      <h1 className="text-2xl font-bold">Home  </h1>
      <h1>your name :{user.firstName} .</h1>
      <h1>Your balance is: {balance} .</h1>
      <h1>token : {token} .</h1>
    </div>
  );
}