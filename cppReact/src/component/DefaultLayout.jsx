import { Outlet, useNavigate } from "react-router-dom";
import { useStateContext } from "../context/ContextProvider";
import { useEffect } from "react";

export default function DefaultLayout() {
  const navigate=useNavigate();
  const {setUser,setToken}=useStateContext();
  const handleLogout=()=>{
    setUser(null);
    setToken(null);
    navigate('/');
  }
  useEffect(()=>{
    if(!localStorage.getItem('ACCESS_TOKEN')){
      navigate('/login');
    }
  },[])

  return (
    <>
    <div className="p-4 border-b border-gray-300">
      <header className="flex justify-between items-center">
        <div>
          <h1 className="text-xl font-bold">User Panel</h1>
        
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