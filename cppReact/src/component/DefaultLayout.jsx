import { Outlet } from "react-router-dom";

export default function DefaultLayout() {
  return (
    <>
    <div className="p-4 border-b border-gray-300">
        <h1 className="text-lg text-green-500 font-bold">Default Layout</h1>
    </div>
    <main className="p-4">
        <Outlet/>
    </main>
    </>
  );
}