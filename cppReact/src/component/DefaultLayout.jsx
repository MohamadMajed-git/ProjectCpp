import { Outlet, useNavigate } from "react-router-dom";
import { useStateContext } from "../context/ContextProvider";
import { useEffect } from "react";
import BankLogo from '../assets/BankLogo.png';
import { ShieldCheck } from "lucide-react";


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
        <div className="flex items-center gap-2">
          <div className="bg-blue-600 p-2 rounded-lg">
            <ShieldCheck className="text-white" size={24} />
          </div>
          <span className="text-xl font-bold tracking-tight text-slate-800">TRUST<span className="text-blue-600">BANK</span></span>
        </div>
        <div>
          <h1 className="text-xl font-bold text-gray-800 ">User Panel</h1>
        
        </div>
        <div>
          <button className="bg-red-600 hover:bg-red-700 text-white px-6 py-2 rounded-full text-sm font-semibold shadow-lg shadow-blue-200 transition-all active:scale-95 "
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