import { UserCircle, Mail, CreditCard, Phone, Briefcase, Calendar, Home, Hash, ShieldCheck } from "lucide-react";
import { useStateContext } from "../context/ContextProvider";

export default function Profile() {
  const { user } = useStateContext();

  const InfoRow = ({ icon, label, value }) => (
    <div className="flex items-start gap-4 p-3 rounded-lg hover:bg-blue-50 transition">
      <div className="p-2 bg-blue-100 rounded-lg text-blue-600">{icon}</div>
      <div>
        <p className="text-xs uppercase tracking-wider text-gray-400 font-medium">{label}</p>
        <p className="text-base font-semibold text-gray-700">{value}</p>
      </div>
    </div>
  );

  return (
    <div className="min-h-screen bg-gray-50 p-6 md:p-10">
      <div className="max-w-4xl mx-auto space-y-8">
        <header className="flex items-center gap-4">
          <div className="p-3 bg-gradient-to-br from-blue-700 to-blue-500 rounded-xl shadow-lg shadow-blue-200">
            <UserCircle className="w-8 h-8 text-white" />
          </div>
          <div>
            <h1 className="text-3xl font-bold text-gray-900">User Profile</h1>
            <p className="text-gray-500">Account information overview</p>
          </div>
        </header>

        {/* Personal Info */}
        <div className="bg-white rounded-2xl border border-blue-100 shadow-sm overflow-hidden">
          <div className="px-6 py-4 bg-blue-50/30 border-b border-blue-100 flex items-center gap-2">
            <ShieldCheck className="w-5 h-5 text-blue-600" />
            <h2 className="font-semibold text-gray-800">Personal Information</h2>
          </div>
          <div className="p-6 grid grid-cols-1 md:grid-cols-2 gap-4">
            <InfoRow icon={<UserCircle size={20} />} label="First Name" value={user.firstName} />
            <InfoRow icon={<UserCircle size={20} />} label="Last Name" value={user.lastName} />
            <InfoRow icon={<CreditCard size={20} />} label="National ID" value={user.nationalID} />
            <InfoRow icon={<Calendar size={20} />} label="Birthday" value={user.birthday} />
            <InfoRow icon={<Home size={20} />} label="Address" value={user.address} />
            <InfoRow icon={<Phone size={20} />} label="Phone" value={user.phone} />
            <InfoRow icon={<Briefcase size={20} />} label="Job" value={user.job} />
            <InfoRow icon={<Calendar size={20} />} label="Created At" value={user.createdAt} />
          </div>
        </div>

        {/* Account Info */}
        <div className="bg-white rounded-2xl border border-blue-100 shadow-sm overflow-hidden">
          <div className="px-6 py-4 bg-blue-50/30 border-b border-blue-100 flex items-center gap-2">
            <Hash className="w-5 h-5 text-blue-600" />
            <h2 className="font-semibold text-gray-800">Account Details</h2>
          </div>
          <div className="p-6 grid grid-cols-1 md:grid-cols-2 gap-4">
            <InfoRow icon={<Mail size={20} />} label="Email" value={user.email} />
            <InfoRow icon={<ShieldCheck size={20} />} label="Account Type" value={user.accountType} />
            <InfoRow icon={<Hash size={20} />} label="Account Number" value={user.accountNumber} />
          </div>
        </div>

      </div>
    </div>
  );
}