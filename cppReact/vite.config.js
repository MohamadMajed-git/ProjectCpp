import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import tailwindcss from '@tailwindcss/vite'

// https://vite.dev/config/
export default defineConfig({
  plugins: [
    react(),
    tailwindcss(),
  ],
  // إعدادات السيرفر والبروكسي لحل مشكلة CORS
  server: {
    proxy: {
      '/api': {
        target: 'http://localhost:10000', // رابط سيرفر C++
        changeOrigin: true,
        secure: false,
      }
    }
  }
})