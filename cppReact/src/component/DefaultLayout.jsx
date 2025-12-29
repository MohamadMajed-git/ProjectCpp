import { Outlet, useNavigate } from "react-router-dom";
import { useStateContext } from "../context/ContextProvider";
import { useEffect, useState } from "react";
import BankLogo from '../assets/BankLogo.png';
import { ShieldCheck, Bell, Check, CheckCheck } from "lucide-react";
import axios from "axios";
import axiosClient from "../axiosClient";


/* ===================== ADDED NOTIFICATION COMPONENT ===================== */
function Notifications({ email }) {
  const [open, setOpen] = useState(false);
  const [list, setList] = useState([]);
  const [loading, setLoading] = useState(false); // ✅ FIXED

  const fetchNotifications = () => {
    setLoading(true);
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
        <div className="absolute right-0 mt-2 w-80 bg-white shadow-xl rounded-xl border z-50">
          <div className="flex justify-between items-center px-4 py-2 border-b">
            <span className="font-semibold text-sm">Notifications</span>
            <button
              onClick={markAllRead}
              title="Mark all as read"
              className="text-blue-600 hover:text-blue-800 flex items-center gap-1 text-xs"
            >
              <CheckCheck size={14} />
              Read all
            </button>
          </div>

          <div className="max-h-64 overflow-y-auto">
            {loading && (
              <p className="text-center text-gray-400 text-sm py-4">
                Loading...
              </p>
            )}

            {!loading && list.length === 0 && (
              <p className="text-center text-gray-400 text-sm py-4">
                No notifications
              </p>
            )}

          {list.map(n => (
            <div
              key={n.id}
              className={`flex justify-between items-center px-4 py-3 border-b text-sm cursor-pointer transition-colors duration-200
                ${n.states === 0 ? "bg-gray-100 hover:bg-gray-200" : "bg-white hover:bg-gray-100"}`}
            >
              <span className={`text-gray-800 ${n.states === 0 ? "font-medium" : ""}`}>
                {n.message}
              </span>

              {n.states === 0 && (
                <span
                  title="Mark as read"
                  onClick={() => markRead(n.id)}
                  className="ml-2 text-blue-500 text-[10px] font-bold cursor-pointer"
                >
                  &#10003;&#10003;
                </span>
              )}
            </div>
          ))}





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

          <div className="flex items-center gap-3">
            <Notifications email={user?.email} />

            <button
              className="bg-red-600 hover:bg-red-700 text-white px-6 py-2 rounded-full text-sm font-semibold shadow-lg shadow-blue-200 transition-all active:scale-95"
              onClick={handleLogout}
            >
              log out
            </button>
          </div>

        </header>
      </div>

      <main className="p-4">
        <Outlet />
      </main>
    </>
  );
}
