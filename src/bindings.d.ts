// filename: webview-custom.d.ts

// Extend the global Window interface with custom properties
declare global {
  interface Window {
    // Define the function signature for 'count'
    count(direction: number): Promise<string>
  }
}

// This export is here to ensure this file is treated as a module and not a script
export {}
