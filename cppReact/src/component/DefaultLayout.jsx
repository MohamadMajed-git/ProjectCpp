import { Outlet, useNavigate } from "react-router-dom";
import { useStateContext } from "../context/ContextProvider";
import { useEffect, useState } from "react";
import BankLogo from '../assets/BankLogo.png';
import { ShieldCheck, Bell, Check, CheckCheck, BellOff, Info, Circle, ChevronDown,User, LogOut} from "lucide-react";
import axios from "axios";
import axiosClient from "../axiosClient";


/* ===================== ADDED NOTIFICATION COMPONENT ===================== */
function Notifications({ email }) {
  const [open, setOpen] = useState(false);
  const [list, setList] = useState([]);
  const [loading, setLoading] = useState(false); // ✅ FIXED
  const hasPostedRef = useState(false);

  const fetchNotifications = () => {
    setLoading(true);
    if(hasPostedRef.current) {
      setLoading(false);
      return;
    }
    hasPostedRef.current = true;
    axiosClient
      .get(`client/get-notifications?email=${email}`) // ✅ FIXED
      .then((res) => setList(res.data || []))
      .finally(() => setLoading(false));
  };
  
useEffect(() => {
  if (email) {
    fetchNotifications();
  }
}, [email]);


  const markRead = async (id) => {
    await axios.post(`/api/notifications/read`, { id });
    setList(prev => prev.map(n => n.id === id ? { ...n, states: 1 } : n));
  };

  const markAllRead = async () => {
    await axios.post(`/api/notifications/read-all`, { email });
    setList(prev => prev.map(n => ({ ...n, states: 1 })));
  };

  return (
    <div className="relative">
      <button
        onClick={() => {
          setOpen(!open);
          fetchNotifications();
        }}
        className="relative p-2 rounded-full hover:bg-gray-100 transition"
      >
        <Bell />
        {list.some(n => n.states === 0) && (
          <span className="absolute top-1 right-1 w-2 h-2 bg-red-500 rounded-full"></span>
        )}
      </button>

{open && (
  <div className="absolute right-0 mt-3 w-96 bg-white shadow-2xl rounded-2xl border border-slate-100 z-50 overflow-hidden transform transition-all">
    {/* Header */}
    <div className="flex justify-between items-center px-5 py-4 bg-slate-50/50 border-b border-slate-100">
      <div className="flex items-center gap-2">
        <Bell size={18} className="text-slate-600" />
        <span className="font-bold text-slate-800 text-sm">Notifications</span>
      </div>
      <button
        onClick={markAllRead}
        className="text-blue-600 hover:text-blue-700 hover:bg-blue-50 px-2 py-1 rounded-md transition-colors flex items-center gap-1.5 text-xs font-medium"
      >
        <CheckCheck size={14} />
       make all read
      </button>
    </div>

    {/* Notifications List */}
    <div className="max-h-[400px] overflow-y-auto custom-scrollbar">
      {loading && (
        <div className="flex flex-col items-center justify-center py-10 gap-2">
          <div className="animate-spin rounded-full h-6 w-6 border-b-2 border-blue-600"></div>
          <p className="text-slate-400 text-xs">Loading...</p>
        </div>
      )}

      {!loading && list.length === 0 && (
        <div className="flex flex-col items-center justify-center py-12 text-slate-400">
          <BellOff size={40} strokeWidth={1.5} className="mb-2 opacity-20" />
          <p className="text-sm">No new notifications</p>
        </div>
      )}

      {!loading && list.map((n) => (
        <div
          key={n.id}
          onClick={() => n.states === 0 && markRead(n.id)}
          className={`group flex items-start gap-3 px-5 py-4 border-b border-slate-50 cursor-pointer transition-all duration-200
            ${n.states === 0 ? "bg-blue-50/30 hover:bg-blue-50/60" : "bg-white hover:bg-slate-50"}`}
        >
          {/* Icon based on status */}
          <div className={`mt-1 p-2 rounded-full ${n.states === 0 ? "bg-blue-100 text-blue-600" : "bg-slate-100 text-slate-400"}`}>
            <Info size={16} />
          </div>

          {/* Content */}
          <div className="flex-1 flex flex-col gap-1">
            <div className="flex justify-between items-start gap-2">
              <span className={`text-sm leading-relaxed ${n.states === 0 ? "text-slate-900 font-semibold" : "text-slate-600"}`}>
                {n.message}
              </span>
              {n.states === 0 && (
                <Circle size={8} fill="currentColor" className="text-blue-600 mt-1.5 flex-shrink-0" />
              )}
            </div>
            {/* Time Placeholder */}
            <span className="text-[11px] text-slate-400 uppercase tracking-wider">{n.date}</span>
          </div>

          {/* Mark as read individual button - visible on hover */}
          {n.states === 0 && (
            <button 
              className="opacity-0 group-hover:opacity-100 transition-opacity text-slate-400 hover:text-blue-600"
              title="Mark as read"
            >
              <CheckCheck size={16} />
            </button>
          )}
        </div>
      ))}
    </div>

    {/* Footer */}
    <div className="bg-slate-50/50 p-3 text-center border-t border-slate-100">
        <button className="text-xs font-semibold text-slate-500 hover:text-slate-800 transition-colors">
            Show all notifications
        </button>
    </div>
  </div>
)}
    </div>
  );
}
/* ===================== END ADD ===================== */

export default function DefaultLayout() {
  const navigate = useNavigate();
  const { setUser, setToken, user } = useStateContext();
  const [toggleIcon,setToggleIcon]=useState(false);
  const userInitial = user?.firstName?.[0]?.toUpperCase() || "U";
  const handleLogout = () => {
    setUser(null);
    setToken(null);
    navigate('/');
  };

  useEffect(() => {
    if (!localStorage.getItem('ACCESS_TOKEN')) {
      navigate('/login');
    }
  }, []);

  return (
    <>
      <div className="p-4 border-b border-gray-300">
        <header className="flex justify-between items-center">
          <div className="flex items-center gap-2">
            <div className="bg-blue-600 p-2 rounded-lg">
              <ShieldCheck className="text-white" size={24} />
            </div>
            <span className="text-xl font-bold tracking-tight text-slate-800">
              TRUST<span className="text-blue-600">BANK</span>
            </span>
          </div>

          <div>
            <h1 className="text-xl font-bold text-gray-800">User Panel</h1>
          </div>


<div className="flex items-center gap-4">
      <Notifications email={user?.email} />

      <div className="relative">
        
        <button
          onClick={() => setToggleIcon(!toggleIcon)}
          className={`flex items-center gap-2 p-1 pr-3 rounded-full transition-all duration-200 border 
            ${toggleIcon ? 'bg-gray-50 border-gray-300 ring-2 ring-gray-100' : 'bg-white border-transparent hover:bg-gray-50'}`}
        >
          <div className="w-9 h-9 flex items-center justify-center rounded-full bg-indigo-600 text-white shadow-sm font-bold text-sm">
            {userInitial}
          </div>
          
          <ChevronDown 
            size={16} 
            className={`text-gray-500 transition-transform duration-200 ${toggleIcon ? 'rotate-180' : ''}`} 
          />
        </button>

        {toggleIcon && (
          <>
            <div 
              className="fixed inset-0 z-10" 
              onClick={() => setToggleIcon(false)}
            ></div>

            <div className="absolute right-0 top-12 w-64 bg-white rounded-xl shadow-xl border border-gray-100 z-20 overflow-hidden animate-in fade-in zoom-in-95 duration-100">
              
              <div className="px-4 py-3 border-b border-gray-100 bg-gray-50/50">
                <p className="text-sm font-semibold text-gray-900 truncate">
                  {user?.firstName || "User"}
                </p>
                <p className="text-xs text-gray-500 truncate">
                  {user?.email || "No email"}
                </p>
              </div>

              <div className="p-2 flex flex-col gap-1">
                <button
                  onClick={() => {
                    navigate("/profile");
                    setToggleIcon(false);
                  }}
                  className="flex items-center gap-3 w-full px-3 py-2 text-sm font-medium text-gray-700 rounded-lg hover:bg-gray-100 transition-colors"
                >
                  <User size={18} className="text-gray-500" />
                  Profile
                </button>

                <div className="h-px bg-gray-100 my-1 mx-2"></div>

                <button
                  onClick={handleLogout}
                  className="flex items-center gap-3 w-full px-3 py-2 text-sm font-medium text-red-600 rounded-lg hover:bg-red-50 transition-colors"
                >
                  <LogOut size={18} />
                  Log out
                </button>
              </div>
            </div>
          </>
        )}
      </div>
    </div>

        </header>
      </div>

      <main className="p-4">
        <Outlet />
      </main>
    </>
  );
}
