import { Outlet, useNavigate } from "react-router-dom";
import { useStateContext } from "../context/ContextProvider";
import { useEffect } from "react";

export default function ADefaultLayout() {
    const navigate=useNavigate();
  const {user,setUser,setToken}=useStateContext();
  const handleLogout=()=>{
    setUser(null);
    setToken(null);
    navigate('/');
  }
  useEffect(()=>{
    if(!localStorage.getItem('ACCESS_TOKEN')){
      navigate('/login');
    }
    if(user&&user.nationalID!="123456789123"){
      navigate('/');
    }
  },[])
  
    return (
    <>
    <div className="p-4 border-b border-gray-300">
      <header className="flex justify-between items-center">
        <div>
          <h1 className="text-xl font-bold">Admin Panel</h1>
        
        </div>
        <div>
          <button className="bg-red-500 p-2 rounded hover:bg-red-400 text-white "
          onClick={handleLogout}
          >log out</button>
        </div>

      </header>

    </div>
    <main className="p-4">
        <Outlet/>
    </main>
    </>
  );
}