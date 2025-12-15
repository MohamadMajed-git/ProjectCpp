import { useNavigate } from "react-router-dom";
import { ShieldAlert, History, Building2, KeyRound, LayoutDashboard } from 'lucide-react';

export default function AHome() {
  const navigate = useNavigate();

const menuItems = [
    {
      title: "Holded Accounts",
      path: "/admin/holded-accounts",
      icon: <ShieldAlert size={32} />,
      color: "text-red-600",
      bg: "bg-red-50",
      description: "Manage suspended and frozen user accounts"
    },
    {
      title: "All Transactions",
      path: "/admin/all-transactions",
      icon: <History size={32} />,
      color: "text-blue-600",
      bg: "bg-blue-50",
      description: "View and audit all system financial transactions"
    },
    {
      title: "Branches Management",
      path: "/admin/branches",
      icon: <Building2 size={32} />,
      color: "text-purple-600",
      bg: "bg-purple-50",
      description: "Add, edit, or remove bank branches"
    },
    {
      title: "Password Requests",
      path: "/admin/password-change-requests",
      icon: <KeyRound size={32} />,
      color: "text-orange-600",
      bg: "bg-orange-50",
      description: "Review pending password reset requests"
    },
    {
      title: "Handle Loan Requests",
      path: "/admin/handle-loan-request",
      icon: <ShieldAlert size={32} />,
      color: "text-green-600",
      bg: "bg-green-50",
      description: "Approve or deny user loan applications"
    }
  ];

  return (
<div className="min-h-screen bg-gray-50 p-8">
      <div className="max-w-6xl mx-auto mb-10">
        <div className="flex items-center gap-3 mb-2">
          <LayoutDashboard className="text-gray-700" size={28} />
          <h1 className="text-3xl font-bold text-gray-800">Admin Dashboard</h1>
        </div>
        <p className="text-gray-500">Welcome back, Administrator. Select a module to manage.</p>
      </div>

      <div className="max-w-6xl mx-auto grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-6">
        {menuItems.map((item, index) => (
          <div
            key={index}
            onClick={() => navigate(item.path)}
            className="bg-white p-6 rounded-xl shadow-sm hover:shadow-md border border-gray-100 cursor-pointer transition-all duration-300 transform hover:-translate-y-1 group"
          >
            <div className={`w-14 h-14 rounded-full flex items-center justify-center mb-4 ${item.bg} ${item.color} group-hover:scale-110 transition-transform duration-300`}>
              {item.icon}
            </div>
            <h2 className="text-xl font-semibold text-gray-800 mb-2 group-hover:text-blue-600 transition-colors">
              {item.title}
            </h2>
            <p className="text-sm text-gray-500 leading-relaxed">
              {item.description}
            </p>
          </div>
        ))}
      </div>
    </div>
    
  );
}