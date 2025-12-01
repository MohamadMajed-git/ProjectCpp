import { useEffect } from "react";
import { Outlet, useNavigate } from "react-router-dom";
import { useStateContext } from "../context/ContextProvider";

export default function GuestLayout() {
    const {token}=useStateContext();
    const navigate=useNavigate();
    useEffect(()=>{
        if(token){
            navigate('/home');
        }
    },[])
  return (


    <>

        <div>
      <header className="flex justify-between items-center p-4">
        <div>
          <h1 className="text-2xl font-bold">Guest Layout</h1>

        </div>
        <div className="flex gap-2">
            <div>
            <button className="bg-blue-500 rounded p-2 hover:bg-blue-400 "
            onClick={()=>{navigate("/signup")}}
            >signup</button>
            </div>
            <div>
            <button className="bg-blue-500 rounded p-2 hover:bg-blue-400"
            onClick={()=>{navigate("/login")}}
            >login</button>
            </div>
        </div>
      </header>
    </div>
    <main>
      <Outlet />
    </main>
    </>
  );
}