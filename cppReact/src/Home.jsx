import { useNavigate } from "react-router-dom";
import { useStateContext } from "./context/ContextProvider";
import { useEffect } from "react";

export default function Home() {
  const {user,token}=useStateContext();
  const navigate = useNavigate();
  useEffect(()=>{
  if(user&&user.nationalID=="123456789123"){
    navigate('/admin/admin-home')
  }
  },[])
  
  console.log(user);
  return (
    
    <div>
      <h1 className="text-2xl font-bold">Home  </h1>
      <h1>{user.firstName} .</h1>
      <h1>{token} .</h1>
    </div>
  );
}